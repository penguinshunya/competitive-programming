import glob
import json
import os
import re
import subprocess
import uuid

CXX = "g++-9"
SNIPPET_DIRECTORY = "./snippets/"
HEADER_FILE = "header.hpp"

def execute_test(file):
  with open(file, "r") as f:
    text = f.read()
    if "void test" not in text:
      return
  content = [
    '#include "{0}"'.format(file),
    "int main() {",
    "  test();",
    "  return 0;",
    "}",
  ]
  text = "\n".join(content)
  main_file = str(uuid.uuid4()) + ".cpp"
  exec_file = str(uuid.uuid4())
  with open(main_file, "w") as f:
    f.write(text)
  try:
    subprocess.run([CXX, main_file, "-o", exec_file], check=True)
    subprocess.run(["./" + exec_file], check=True)
    print("passed the test in {0}".format(file))
  except Exception as e:
    print("failed the test in {0}".format(file))
    raise e
  finally:
    for file in [main_file, exec_file]:
      os.remove(file)

def make_template():
  body = []
  with open(os.path.join(SNIPPET_DIRECTORY, HEADER_FILE), "r") as f:
    text = f.read()
    body = text.split("\n")
  body.extend([
    "int main() {",
    "  ios::sync_with_stdio(0);",
    "  cin.tie(0);",
    "  cout << fixed << setprecision(12);",
    "  cerr << fixed << setprecision(12);",
    "  $0",
    "  return 0;",
    "}",
  ])
  content = {
    "prefix": "cpt",
    "body": body
  }
  return content    

def delete_unnecessary_information(text):
  text = text.replace('#include "{0}"'.format(HEADER_FILE), '')
  text = re.sub(r"void test\(\) \{[^}]+\}", "", text)
  text = text.strip()
  return text

output = {}
output["cpt"] = make_template()

for file in glob.glob(os.path.join(SNIPPET_DIRECTORY, "*.cpp")):
  execute_test(file)
  name = os.path.splitext(os.path.basename(file))[0]
  body = []
  with open(file) as f:
    text = f.read()
    text = delete_unnecessary_information(text)
    body = text.split("\n")
  content = {
    "prefix": name,
    "body": body
  }
  output[name] = content

with open("cpp.json", "w") as f:
  f.write(json.dumps(output, indent=2))