from datetime import date

import os
import requests
import json

"""
This program gets list of file names from 'algorithm-solution' directory and makes list of solved problems.
Then it sorts problems by what algorithms used and makes dictionary through solved.ac API.
It gets all contents from README_BASE.md, and attaches algorithm section and <a> tag according to the dictionary. 
"""

# Allowed extensions
extensions = ["cpp", "py"]

# Get problem number list from folder 'algorithm-solution'
file_list = os.listdir("./algorithm-solution")
problems = []
for file in file_list:
    if file.split(".")[1] in extensions:
        problems.append(file.split(".")[0])

# Get a mapping from bojTagId to bogTagName.
url = "https://solved.ac/api/v3/tag/list"
response = requests.request("GET", url, headers={"Content-Type": "application/json"})
info = json.loads(response.text)
id_name_dict = dict()
for t in info["items"]:
    for n in t["displayNames"]:
        if n["language"] == "en":
            id_name_dict[t["bojTagId"]] = " ".join(list(map(lambda s: s.capitalize(), n["name"].split(" "))))

# Get information of solved problems.
url = "https://solved.ac/api/v3/problem/lookup"
querystring = {"problemIds": ','.join(problems)}
response = requests.request("GET", url, headers={"Content-Type": "application/json"}, params=querystring)
info = json.loads(response.text)

# Make a dictionary, BOJ tag for key and problem ID and title for value.
tag_problem_dict = dict()
for p in info:
    for t in list(map(lambda x: id_name_dict[x["bojTagId"]], p["tags"])):
        if t not in tag_problem_dict:
            tag_problem_dict[t] = []
        tag_problem_dict[t].append(str(p["problemId"]) + "번: " + p["titleKo"])

# Get all content of README_BASE.md
f = open("./README_BASE.md")
content = f.readlines()
f.close()

# Write new README.md
f = open("./README.md", "w", encoding="UTF-8")
for line in content:
    f.write(line)
f.write("\n## Solved Problems\n")
for key, value in sorted(tag_problem_dict.items()):
    f.write("### " + key + "\n")
    for v in sorted(value):
        f.write('* <a href="https://www.acmicpc.net/problem/{0}"> {1}</a>\n'.format(v.split(":")[0][:-1], v))
    f.write("\n")
f.close()

# Automatically git add/commit/push solved problems.
os.system("git add README.md")
os.system("git commit -m " + date.today().strftime('"%Y.%m.%d. Update README.md (Automatically)"'))
os.system("git add .")
os.system("git commit -m " + date.today().strftime('"%Y.%m.%d. Solve problem (Automatically)"'))
os.system("git push")
