#define NOB_IMPLEMENTATION
#include "./include/nob.h"

const char *build_path = "./build";
const char *build_static_path = "./build/static";

void cc(Nob_Cmd *cmd)
{
  nob_cmd_append(cmd, "cc");
}

void warnings(Nob_Cmd *cmd)
{
  nob_cmd_append(cmd, "-Wall", "-Wextra", "-ggdb");
}

Nob_Proc simple_glfw()
{
  Nob_Cmd cmd = {0};
  cc(&cmd);
  warnings(&cmd);
  nob_cmd_append(&cmd, "-o", "./build/simple_glfw");
  nob_cmd_append(&cmd, "./glfw-test/simple.c");
  nob_cmd_append(&cmd, "-L./build/static/");
  nob_cmd_append(&cmd, "-lglfw", "-lrt", "-lm", "-ldl", "-lGL");
  return nob_cmd_run_async(cmd);
}

bool build_glfw()
{

  Nob_File_Paths object_files = {0};
  Nob_Cmd cmd = {0};
  Nob_Procs procs = {0};

  const char *glfw_build_path = nob_temp_sprintf("%s/%s", build_path, "glfw_build");

  if (!nob_mkdir_if_not_exists(glfw_build_path))
  {
    nob_log(NOB_ERROR, "error");
    return false;
  }

  static const char *glfw_modules[] = {
      // "cocoa_time",
      "context",
      "egl_context",
      "glx_context",
      "init",
      "input",
      "linux_joystick",
      "monitor",
      "null_init",
      "null_joystick",
      "null_monitor",
      "null_window",
      "osmesa_context",
      "platform",
      "posix_module",
      "posix_poll",
      "posix_thread",
      "posix_time",
      "vulkan",
      "wgl_context",
      // "win32_init",
      // "win32_joystick",
      // "win32_module",
      // "win32_monitor",
      // "win32_thread",
      // "win32_time",
      // "win32_window",
      "window",
      // "wl_init",
      // "wl_monitor",
      // "wl_window",
      "x11_init",
      "x11_monitor",
      "x11_window",
      "xkb_unicode",
  };

  for (size_t i = 0; i < NOB_ARRAY_LEN(glfw_modules); ++i)
  {
    const char *input_path = nob_temp_sprintf("./glfw/src/%s.c", glfw_modules[i]);
    const char *output_path = nob_temp_sprintf("%s/%s.o", glfw_build_path, glfw_modules[i]);
    output_path = nob_temp_sprintf("%s/%s.o", glfw_build_path, glfw_modules[i]);

    nob_da_append(&object_files, output_path);

    if (nob_needs_rebuild(output_path, &input_path, 1))
    {
      cmd.count = 0;
      cc(&cmd);
      nob_cmd_append(&cmd, "-ggdb", "-fPIC");
      nob_cmd_append(&cmd, "-I./glfw/include/");
      nob_cmd_append(&cmd, "-I./glfw/src/");
      nob_cmd_append(&cmd, "-c", input_path);
      nob_cmd_append(&cmd, "-o", output_path);
      Nob_Proc proc = nob_cmd_run_async(cmd);
      nob_da_append(&procs, proc);
    }
  }

  cmd.count = 0;

  if (!nob_procs_wait(procs))
  {
    nob_log(NOB_ERROR, "error");
    return false;
  }

  // return true;
  const char *libglfw_path = nob_temp_sprintf("%s/libglfw.so", build_static_path);

  if (nob_needs_rebuild(libglfw_path, object_files.items, object_files.count))
  {
    nob_cmd_append(&cmd, "cc");
    nob_cmd_append(&cmd, "-shared");
    nob_cmd_append(&cmd, "-o", libglfw_path);
    for (size_t i = 0; i < NOB_ARRAY_LEN(glfw_modules); ++i)
    {
      const char *input_path = nob_temp_sprintf("%s/%s.o", glfw_build_path, glfw_modules[i]);
      nob_cmd_append(&cmd, input_path);
    }
    if (!nob_cmd_run_sync(cmd))
    {
      nob_log(NOB_ERROR, "error");
      return false;
    }
  }

  return nob_cmd_run_async(cmd);
}

int main(int argc, char **argv)
{
  NOB_GO_REBUILD_URSELF(argc, argv);
  if (!nob_mkdir_if_not_exists(build_path))
    return 1;

  if (!nob_mkdir_if_not_exists(build_static_path))
    return 1;

  if (!build_glfw())
    return 1;

  Nob_Procs procs = {0};

  nob_da_append(&procs, simple_glfw());

  if (!nob_procs_wait(procs))
    return 1;
  return 0;
}
