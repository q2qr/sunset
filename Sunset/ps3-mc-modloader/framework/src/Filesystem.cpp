#include "../include/Filesystem.h"

#include <cell/cell_fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* kSunsetMagic = "SUNSETPK";
static const uint32_t kSunsetVersion = 1;
static const char* kExtractDir = "/dev_hdd0/tmp/ps3_mc_modloader/";

static void SafeCopy(char* dst, size_t dstSize, const char* src)
{
    if (!dst || dstSize == 0) {
        return;
    }
    if (!src) {
        dst[0] = '\0';
        return;
    }
    strncpy(dst, src, dstSize - 1);
    dst[dstSize - 1] = '\0';
}

static bool EndsWith(const char* value, const char* suffix)
{
    if (!value || !suffix) {
        return false;
    }
    size_t valueLen = strlen(value);
    size_t suffixLen = strlen(suffix);
    if (suffixLen > valueLen) {
        return false;
    }
    return strcmp(value + (valueLen - suffixLen), suffix) == 0;
}

static uint32_t ReadU32LE(const uint8_t* in)
{
    return ((uint32_t)in[0]) |
           ((uint32_t)in[1] << 8) |
           ((uint32_t)in[2] << 16) |
           ((uint32_t)in[3] << 24);
}

static bool EnsureDirectory(const char* path)
{
    int rc = cellFsMkdir(path, 0777);
    return rc == CELL_FS_SUCCEEDED || rc == CELL_FS_EEXIST;
}

static bool ReadEntireFile(const char* path, uint8_t** outData, uint64_t* outSize)
{
    if (!path || !outData || !outSize) {
        return false;
    }

    *outData = 0;
    *outSize = 0;

    int fd = -1;
    if (cellFsOpen(path, CELL_FS_O_RDONLY, &fd, 0, 0) != CELL_FS_SUCCEEDED) {
        return false;
    }

    uint64_t size = 0;
    if (cellFsLseek(fd, 0, CELL_FS_SEEK_END, &size) != CELL_FS_SUCCEEDED ||
        cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &size) != CELL_FS_SUCCEEDED) {
        cellFsClose(fd);
        return false;
    }

    if (size == 0 || size > 4 * 1024 * 1024) {
        cellFsClose(fd);
        return false;
    }

    uint8_t* buffer = (uint8_t*)malloc((size_t)size);
    if (!buffer) {
        cellFsClose(fd);
        return false;
    }

    uint64_t totalRead = 0;
    while (totalRead < size) {
        uint64_t chunkRead = 0;
        int rc = cellFsRead(fd, buffer + totalRead, size - totalRead, &chunkRead);
        if (rc != CELL_FS_SUCCEEDED || chunkRead == 0) {
            free(buffer);
            cellFsClose(fd);
            return false;
        }
        totalRead += chunkRead;
    }

    cellFsClose(fd);
    *outData = buffer;
    *outSize = size;
    return true;
}

static bool WriteEntireFile(const char* path, const uint8_t* data, uint32_t size)
{
    if (!path || !data || size == 0) {
        return false;
    }

    int fd = -1;
    int rc = cellFsOpen(path, CELL_FS_O_CREAT | CELL_FS_O_TRUNC | CELL_FS_O_WRONLY, &fd, 0, 0);
    if (rc != CELL_FS_SUCCEEDED) {
        return false;
    }

    uint64_t totalWritten = 0;
    while (totalWritten < size) {
        uint64_t written = 0;
        rc = cellFsWrite(fd, data + totalWritten, size - totalWritten, &written);
        if (rc != CELL_FS_SUCCEEDED || written == 0) {
            cellFsClose(fd);
            return false;
        }
        totalWritten += written;
    }

    cellFsClose(fd);
    return true;
}

static void GetFileStem(const char* path, char* out, size_t outSize)
{
    out[0] = '\0';
    if (!path || !out || outSize == 0) {
        return;
    }

    const char* file = strrchr(path, '/');
    if (!file) {
        file = strrchr(path, '\\');
    }
    file = file ? file + 1 : path;

    SafeCopy(out, outSize, file);
    char* dot = strrchr(out, '.');
    if (dot) {
        *dot = '\0';
    }
}

static bool ParseJsonValue(const char* json, const char* key, char* out, size_t outSize)
{
    if (!json || !key || !out || outSize == 0) {
        return false;
    }

    char pattern[64];
    snprintf(pattern, sizeof(pattern), "\"%s\"", key);
    const char* keyStart = strstr(json, pattern);
    if (!keyStart) {
        return false;
    }

    const char* colon = strchr(keyStart, ':');
    if (!colon) {
        return false;
    }

    const char* quote = strchr(colon, '"');
    if (!quote) {
        return false;
    }

    ++quote;
    size_t i = 0;
    while (*quote && *quote != '"' && i + 1 < outSize) {
        if (*quote == '\\' && quote[1] != '\0') {
            ++quote;
        }
        out[i++] = *quote++;
    }
    out[i] = '\0';
    return i > 0;
}

int EnumerateModEntries(const char* modPath, char outPaths[][256], int maxCount)
{
    int dirFd = -1;
    if (cellFsOpendir(modPath, &dirFd) != CELL_FS_SUCCEEDED) {
        return 0;
    }

    int found = 0;
    CellFsDirent entry;
    uint64_t nread = 0;

    while (found < maxCount &&
           cellFsReaddir(dirFd, &entry, &nread) == CELL_FS_SUCCEEDED &&
           nread > 0) {
        if (entry.d_name[0] == '.') {
            continue;
        }

        const char* ext = strrchr(entry.d_name, '.');
        if (!ext) {
            continue;
        }

        if (strcmp(ext, ".sprx") != 0 && strcmp(ext, ".sunset") != 0) {
            continue;
        }

        snprintf(outPaths[found], 256, "%s%s", modPath, entry.d_name);
        ++found;
    }

    cellFsClosedir(dirFd);
    return found;
}

bool ExtractSunsetPackage(const char* packagePath, char* outSprxPath, size_t outSprxPathSize, ModPublicInfo* outInfo)
{
    if (!packagePath || !outSprxPath || outSprxPathSize == 0 || !EndsWith(packagePath, ".sunset")) {
        return false;
    }

    outSprxPath[0] = '\0';
    if (outInfo) {
        memset(outInfo, 0, sizeof(*outInfo));
        SafeCopy(outInfo->packagePath, sizeof(outInfo->packagePath), packagePath);
        outInfo->fromSunsetPackage = true;
    }

    uint8_t* data = 0;
    uint64_t size = 0;
    if (!ReadEntireFile(packagePath, &data, &size)) {
        return false;
    }

    bool ok = false;
    do {
        if (size < 16 || memcmp(data, kSunsetMagic, 8) != 0) {
            break;
        }

        uint32_t version = ReadU32LE(data + 8);
        if (version != kSunsetVersion) {
            break;
        }

        uint32_t entryCount = ReadU32LE(data + 12);
        uint64_t offset = 16;

        if (!EnsureDirectory("/dev_hdd0/tmp") || !EnsureDirectory("/dev_hdd0/tmp/ps3_mc_modloader")) {
            break;
        }

        char packageStem[128];
        GetFileStem(packagePath, packageStem, sizeof(packageStem));

        char jsonValue[160] = {0};

        for (uint32_t i = 0; i < entryCount; ++i) {
            if (offset + 12 > size) {
                break;
            }

            uint32_t entryType = ReadU32LE(data + offset); offset += 4;
            uint32_t nameLen = ReadU32LE(data + offset); offset += 4;
            uint32_t dataLen = ReadU32LE(data + offset); offset += 4;

            if (offset + nameLen + dataLen > size || nameLen == 0 || dataLen == 0) {
                break;
            }

            const char* entryName = (const char*)(data + offset);
            offset += nameLen;
            const uint8_t* entryData = data + offset;
            offset += dataLen;

            char sanitizedName[96];
            size_t maxCopy = (nameLen < sizeof(sanitizedName) - 1) ? nameLen : (sizeof(sanitizedName) - 1);
            memcpy(sanitizedName, entryName, maxCopy);
            sanitizedName[maxCopy] = '\0';

            if (entryType == 1) {
                char targetPath[256];
                snprintf(targetPath, sizeof(targetPath), "%s%s_%s", kExtractDir, packageStem, sanitizedName);
                if (!WriteEntireFile(targetPath, entryData, dataLen)) {
                    break;
                }
                SafeCopy(outSprxPath, outSprxPathSize, targetPath);
                if (outInfo) {
                    SafeCopy(outInfo->sprxPath, sizeof(outInfo->sprxPath), targetPath);
                }
            } else if (entryType == 2) {
                char* json = (char*)malloc(dataLen + 1);
                if (!json) {
                    break;
                }
                memcpy(json, entryData, dataLen);
                json[dataLen] = '\0';

                if (outInfo) {
                    ParseJsonValue(json, "name", outInfo->name, sizeof(outInfo->name));
                    ParseJsonValue(json, "author", outInfo->author, sizeof(outInfo->author));
                    ParseJsonValue(json, "version", outInfo->version, sizeof(outInfo->version));
                    ParseJsonValue(json, "description", outInfo->description, sizeof(outInfo->description));
                    if (ParseJsonValue(json, "image", jsonValue, sizeof(jsonValue)) && outInfo->previewImagePath[0] == '\0') {
                        SafeCopy(outInfo->previewImagePath, sizeof(outInfo->previewImagePath), jsonValue);
                    }
                }
                free(json);
            } else if (entryType == 3) {
                char imagePath[256];
                snprintf(imagePath, sizeof(imagePath), "%s%s_%s", kExtractDir, packageStem, sanitizedName);
                if (WriteEntireFile(imagePath, entryData, dataLen) && outInfo) {
                    SafeCopy(outInfo->previewImagePath, sizeof(outInfo->previewImagePath), imagePath);
                }
            }
        }

        ok = outSprxPath[0] != '\0';
    } while (0);

    free(data);
    return ok;
}



