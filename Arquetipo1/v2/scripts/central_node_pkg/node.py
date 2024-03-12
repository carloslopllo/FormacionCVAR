import os
import re
import sys
import yaml
from jinja2 import Environment, FileSystemLoader

# sys.argv[1] = /home/vboxuser/ros2_ws/manifest/node/manifest.yaml
# sys.argv[2] = /home/vboxuser/ros2_ws/templates/node/

if len(sys.argv) != 3:
	print("Usage:", sys.argv[0], "~/ros2_ws/manifest/node/manifest.yaml", "~/ros2_ws/templates/node/")
	sys.exit(1)

with open(sys.argv[1], "r") as f:
	try:
		yp = yaml.safe_load(f)
	except yaml.YAMLError as e:
		raise ValueError(f"Error while parsing YAML file: {e}")

default_type = "REQUIRED"

for section in ("buildtools", "dependencies", "testing_CMakeLists"):
	if section in yp:
		for item in yp[section]:
			item.setdefault("type", default_type)

for path, _, files in os.walk(sys.argv[2]):
	for file in files:
		environment = Environment(loader=FileSystemLoader(path))
		path_file_template = environment.get_template(file)

		new_path_file = re.sub("/templates/[^/]*?/", "/src/{project_name}/".format(**yp), os.path.join(path, file))
		new_path_file = new_path_file.replace(".jinja2", "")

		try:
			open(new_path_file, mode="w", encoding="utf-8")
		except IOError:
			os.makedirs(os.path.dirname(new_path_file))
		finally:
			with open(new_path_file, mode="w", encoding="utf-8") as results:
				results.write(path_file_template.render(yp))
				print(f"... wrote {new_path_file}")
