#include <python/Python.h>
#include <iostream>

const char* parseVertexShader(const char* file)
{
    const char* result = "";
    std::cout << "done in " << result << std::endl;

    PyObject *pName, *pModule, *pFunc, *pCall, *pArgs, *pValue;
    Py_Initialize();

    PyRun_SimpleString(
    "import sys\n"
    "sys.path.append('.')\n"
);
    pName = PyUnicode_DecodeFSDefault("parse.py");

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL)
    {
        pFunc = PyObject_GetAttrString(pModule, "parseShaderFile");

        if (pFunc && PyCallable_Check(pFunc))
        {
            pArgs = PyTuple_New(2);

            pValue = PyUnicode_FromString(file);
            if (!pValue)
            {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert argument\n");
                return NULL;
            }
            /* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, 0, pValue);

            pValue = PyBool_FromLong(1);
            if (!pValue)
            {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert argument\n");
                return NULL;
            }
            /* pValue reference stolen here: */
            PyTuple_SetItem(pArgs, 1, pValue);

            pCall = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL)
            {
                result = (const char*)_PyUnicode_AsUnicode(pValue);
                printf("Result of call: %s\n", result);
                Py_DECREF(pValue);
            }
            else
            {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return NULL;
            }
        }
        else
        {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", "parseShaderFile");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }

    else
    {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", "parse.py");
        return NULL;
    }

    if (Py_FinalizeEx() < 0)
    {
        return NULL;
    }

    return result;
}


const char* test(const char* file)
{
    Py_Initialize();
    const char* fileStr;

    FILE* fStream;
    fStream = fopen(strcat((char*)"b:", file), "r");

    fclose(fStream);

    Py_Finalize();
}


int main()
{
    printf("heyy\n");
    test("hello.txt");
}