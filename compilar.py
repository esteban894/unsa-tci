import os
import sys
import subprocess

def main():
  if len(sys.argv) < 3:
    print("You must specify the path and file name")
    sys.exit(1)

  route = sys.argv[1]
  files = sys.argv[2:]

  if route.startswith("./"):
      route = route[2:]

  main_file = files[0]
  dependencies = " ".join(files[1:])

  if main_file.endswith('.c'):
    main_file = main_file[:-2]

  source_file_route = f"{route}/{main_file}.c"

  output_file_route = f"{route}/output/{main_file}"
  if (os.name == 'nt'):
    output_file_route += '.exe'

  dependencies_route = ""
  if len(dependencies) > 0:
    for dependency in dependencies.split(" "):
      dependencies_route += f"./{route}/{dependency} "

  if os.name == 'nt':
    route = route.replace('/', '\\')

  build_command = f"gcc -g3 -Wall -Wextra ./{source_file_route} -o ./{output_file_route} -lm {dependencies_route}"

  print(f"Build command:\n{build_command}")

  run_command = f'.\\{route}\\output\\{main_file}' if os.name == "nt" else f"./{route}/output/{main_file}"
  if os.name == "nt":
    run_command += ".exe"
  
  print(f"Run command:\n{run_command}\n\n")

  if(not os.path.exists(f"{route}/output/")):
    os.makedirs(f"{route}/output/")

  print("Compiling...")
  try:
      result = subprocess.run(build_command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
      print(result.stdout)
  except subprocess.CalledProcessError as e:
      print(f"Compilation Error:\n{e.stderr}")
      sys.exit(1)

  print("Successful build. Running...")

  if os.name == "nt":
      os.system("cls")
  else:
      os.system("clear")

  try:
     os.system(run_command)
  except KeyboardInterrupt as e:
    pass

if __name__ == "__main__":
  main()