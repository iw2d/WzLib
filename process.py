import os
import re
import sys


COMMENT_PATTERN = re.compile("[^\n]*//.*\n+", re.MULTILINE)
LIBID_PATTERN = re.compile(
    r"struct\s+__declspec\(uuid\(\"d15c6042-5770-4007-8608-ebf3a1ed8083\"\)\)\s*"
    r"/\*\s*LIBID\s*\*/\s*__WzLib;\n",
    re.MULTILINE
)
TLI_PATTERN = re.compile(r"#include\s+\"([^\"]+\.tli)\"")
IMPORT_MAP = {
    "IWzCanvas": ["IWzSerialize", "IWzProperty"],
    "IWzConvex2D": ["IWzShape2D"],
    "IWzFileSystem": ["IWzWritableNameSpace"],
    "IWzGr2D": ["IWzGr2DLayer"],
    "IWzGr2DLayer": ["IWzCanvas", "IWzVector2D"],
    "IWzPackage": ["IWzSeekableArchive", "IWzNameSpace"],
    "IWzProperty": ["IWzSerialize"],
    "IWzResMan": ["IWzArchive"],
    "IWzSeekableArchive": ["IWzArchive"],
    "IWzSerialize": ["IWzArchive"],
    "IWzShape2D": ["IWzSerialize"],
    "IWzSound": ["IWzSerialize"],
    "IWzUOL": ["IWzSerialize"],
    "IWzVector2D": ["IWzShape2D"],
    "IWzWritableNameSpace": ["IWzNameSpace"]
}


if __name__ == "__main__":
    build_path = sys.argv[1]
    include_path = sys.argv[2]

    if not os.path.isdir(build_path):
        sys.exit(1)

    if not os.path.isdir(include_path):
        os.mkdir(include_path)

    for file_name in os.listdir(build_path):
        interface_name, ext = os.path.splitext(file_name)
        if ext != ".tlh":
            continue

        # print("Processing : " + interface_name)

        # read and process TLH content
        file_path = os.path.join(build_path, file_name)
        with open(file_path, "r", encoding="utf-8") as f:
            tlh_content = f.read()
        tlh_content = tlh_content[tlh_content.find("#pragma once"):]
        tlh_content = tlh_content.replace("      virtual", "    virtual")
        tlh_content = COMMENT_PATTERN.sub("", tlh_content)
        tlh_content = LIBID_PATTERN.sub("", tlh_content)

        # append TLI content
        def replace_tli(match):
            with open(match.group(1), "r", encoding="utf-8") as f:
                tli_content = f.read()
            tli_content = tli_content[(tli_content.find("#pragma once") + len("#pragma once") + 1):]
            tli_content = COMMENT_PATTERN.sub("", tli_content)
            return tli_content
        tlh_content = TLI_PATTERN.sub(replace_tli, tlh_content)

        # append headers
        includes = [
            "#include \"" + name + ".h\""
            for name in IMPORT_MAP.get(interface_name, [])
        ]
        includes.append("#include \"zcomdef.h\"")
        tlh_content = tlh_content.replace("#include <comdef.h>", "\n".join(includes))

        # more replacements
        tlh_content = tlh_content.replace("raw_GetObjectA", "raw_GetObject")
        tlh_content = tlh_content.replace("raw_DrawTextA", "raw_DrawText")
        tlh_content = tlh_content.replace("raw_screenResolution", "put_screenResolution")

        tlh_content = tlh_content.replace("_bstr_t", "Ztl_bstr_t")
        tlh_content = tlh_content.replace("_variant_t", "Ztl_variant_t")
        tlh_content = tlh_content.replace("vtMissing", "vtEmpty")

        # write to header file
        output_path = os.path.join(include_path, interface_name + ".h")
        with open(output_path, "w", encoding="utf-8") as f:
            f.write(tlh_content)