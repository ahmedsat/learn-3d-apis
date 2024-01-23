#define NOB_IMPLEMENTATION
#include "./include/nob/nob.h"

const char *build_path = "./build";
const char *source_path = "./src";

void cc(Nob_Cmd *cmd)
{
  nob_cmd_append(cmd, "cc");
}

void warnings(Nob_Cmd *cmd)
{
  nob_cmd_append(cmd, "-Wall", "-Wextra", "-ggdb");
}

Nob_Proc build_gl(const char *path)
{
  Nob_Cmd cmd = {0};
  cc(&cmd);
  warnings(&cmd);
  nob_cmd_append(&cmd, "-o", nob_temp_sprintf("%s/%s", build_path, path));
  nob_cmd_append(&cmd, nob_temp_sprintf("%s/%s.c", source_path, path));
  nob_cmd_append(&cmd, "-lglfw", "-lGL", "-lGLEW");
  return nob_cmd_run_async(cmd);
}

int main(int argc, char **argv)
{
  NOB_GO_REBUILD_URSELF(argc, argv);
  if (!nob_mkdir_if_not_exists(build_path))
    return 1;

  if (!nob_mkdir_if_not_exists(nob_temp_sprintf("%s/glfw", build_path)))
    return 1;

  if (!nob_mkdir_if_not_exists(nob_temp_sprintf("%s/opengl", build_path)))
    return 1;

  Nob_Procs procs = {0};

  nob_da_append(&procs, build_gl("glfw/simple"));
  nob_da_append(&procs, build_gl("opengl/play"));

  if (!nob_procs_wait(procs))
    return 1;
  return 0;
}
