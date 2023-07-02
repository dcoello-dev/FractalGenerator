#include <Python.h>
#include <nlohmann/json.hpp>
#include "FractalHandler.hpp"

using json = nlohmann::json;


static PyObject* calculate_wrapper (
        PyObject*,
        PyObject* i_args)
{
    int w, h, m;
    if (!PyArg_ParseTuple(i_args, "iii", &w, &h, &m))
    {
        Py_RETURN_FALSE;
    }

    std::vector<int> buffer (w * h, 0);
    std::unique_ptr<Fractal> generator = Fractal_Handler::get_instance(w, h, m);

    generator->calculate(buffer.data());

    json ret {};
    ret["width"] = w;
    ret["height"] = h;
    ret["max"] = m;
    ret["mat"] = buffer;
    return Py_BuildValue("s", ret.dump().c_str());
}

static PyMethodDef METHODS[] = {
    {"calculate", calculate_wrapper, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef Fractal_module = {
    PyModuleDef_HEAD_INIT, "Fractal",
    "",
    -1,
    METHODS,
    NULL,
    NULL,
    NULL,
    NULL
};
PyMODINIT_FUNC PyInit_Fractal(
        void)
{
    return PyModule_Create(&Fractal_module);
}

int main(
        int,
        char* argv[])
{
    wchar_t* program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL)
    {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    if (PyImport_AppendInittab("Fractal", PyInit_Fractal) == -1)
    {
        fprintf(stderr, "Error: could not extend in-built modules \n");
        exit(1);
    }
    Py_SetProgramName(program);
    Py_Initialize();
    PyObject* pmodule = PyImport_ImportModule("Fractal");
    if (!pmodule)
    {
        PyErr_Print();
        fprintf(stderr, "Error: could not import module 'spamn");
    }
    PyMem_RawFree(program);
    return 0;
}
