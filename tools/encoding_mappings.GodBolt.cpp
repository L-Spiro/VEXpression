#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

void parse_gconv_file(const char* path, int *first) {
    FILE* f = fopen(path, "r");
    if (!f) return;

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        // We look for 'alias' and 'module' definitions
        if (strncmp(line, "alias", 5) == 0 || strncmp(line, "module", 6) == 0) {
            char type[16], name[128];
            if (sscanf(line, "%15s %127s", type, name) == 2) {
                // Remove the trailing // found in gconv files
                char* slash = strstr(name, "//");
                if (slash) *slash = '\0';

                // Format as a Python string list item
                if (!*first) printf(",\n    ");
                printf("\"%s\"", name);
                *first = 0;
            }
        }
    }
    fclose(f);
}

int main() {
    const char* paths[] = {
        "/usr/lib/x86_64-linux-gnu/gconv/gconv-modules",
        "/usr/lib/gconv/gconv-modules",
        "/usr/lib64/gconv/gconv-modules"
    };

    printf("test_names = [\n    ");
    int first = 1;

    for (int i = 0; i < 3; i++) {
        parse_gconv_file(paths[i], &first);
    }

    // Check directory-based configs (common in modern Ubuntu/Debian)
    DIR* d = opendir("/usr/lib/x86_64-linux-gnu/gconv/gconv-modules.d");
    if (d) {
        struct dirent* dir;
        while ((dir = readdir(d)) != NULL) {
            if (strstr(dir->d_name, ".conf")) {
                char full[512];
                snprintf(full, sizeof(full), "/usr/lib/x86_64-linux-gnu/gconv/gconv-modules.d/%s", dir->d_name);
                parse_gconv_file(full, &first);
            }
        }
        closedir(d);
    }

    printf("\n]\n");
    return 0;
}
