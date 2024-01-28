#define NOB_IMPLEMENTATION
#include "./include/nob.h"

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

void simple_build_cmd(Nob_Cmd *cmd, const char *path)
{
  cc(cmd);
  warnings(cmd);
  nob_cmd_append(cmd, "-I./include/");
  nob_cmd_append(cmd, "-o", nob_temp_sprintf("%s/%s", build_path, path));
  nob_cmd_append(cmd, nob_temp_sprintf("%s/%s.c", source_path, path));
}

Nob_Proc build_game(const char *path)
{
  Nob_Cmd cmd = {0};
  simple_build_cmd(&cmd, path);
  nob_cmd_append(&cmd, nob_temp_sprintf("%s/%s.c", source_path, "gl-frame/frame"));
  nob_cmd_append(&cmd, nob_temp_sprintf("%s/%s.c", source_path, "gl-frame/init"));
  nob_cmd_append(&cmd, nob_temp_sprintf("%s/%s.c", source_path, "utils/file"));
  nob_cmd_append(&cmd, "-lglfw", "-lGL", "-lGLEW");
  return nob_cmd_run_async(cmd);
}

Nob_Proc build_simple_c_file(const char *path)
{
  Nob_Cmd cmd = {0};
  simple_build_cmd(&cmd, path);
  return nob_cmd_run_async(cmd);
}

Nob_Proc build_simple_c_file_with_utils(const char *path)
{
  Nob_Cmd cmd = {0};
  simple_build_cmd(&cmd, path);
  nob_cmd_append(&cmd, nob_temp_sprintf("%s/%s.c", source_path, "utils/file"));
  return nob_cmd_run_async(cmd);
}

int main(int argc, char **argv)
{
  NOB_GO_REBUILD_URSELF(argc, argv);
  if (!nob_mkdir_if_not_exists(build_path))
    return 1;

  if (!nob_mkdir_if_not_exists(nob_temp_sprintf("%s/examples", build_path)))
    return 1;

  Nob_Procs procs = {0};

  // nob_da_append(&procs, build_game("examples/simple"));
  nob_da_append(&procs, build_game("examples/triangle"));

  if (!nob_procs_wait(procs))
    return 1;
  return 0;
}
