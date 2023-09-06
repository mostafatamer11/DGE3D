# this file is js to return a shader file string
import sys

def parseShaderFile(filePath: str, isVert: bool):
    result = ""
    try:
        with open(filePath, "r") as file:
            file = file.readlines()
            for line in file:
                if "#shader" in line:
                    if "vertex" in line and isVert:
                        while True:
                            if "#shader fragment" in line:
                                break
                            result += line if not "#shader" else ""

                    elif not ("fragment" in line) and not isVert:
                        while True:
                            if "#shader vertex" in line:
                                break
                            result += line if not "#shader" else ""

    except FileNotFoundError:
        print(f"PARSE.PY [ERROR]:\nFILE NOT FOUND {filePath}\n", file=sys.stderr, end="")
        sys.stderr.flush()
        return ""

    except:
        print(f"PARSE.PY [ERROR]:\nNOT EXPECTED ERROR\n", file=sys.stderr, end="")
        sys.stderr.flush()

    return result


parseShaderFile("hello.txt", True)