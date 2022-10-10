import os
import requests
from bs4 import BeautifulSoup
import json

"""
This program gets list of file names from 'algorithm-solution' directory and makes list of solved problems.
Then it sorts problems by what algorithms used and makes dictionary through solved.ac API.
It gets all contents from README_BASE.md, and attaches algorithm section and <a> tag according to the dictionary. 
"""

# Make dictionary to convert Korean tags to English
ko_to_en = dict()
res = requests.get("https://www.acmicpc.net/problem/tags")
soup = BeautifulSoup(res.content, "html.parser")
tags = soup.find_all("td")
for i in range(len(tags)):
    if i % 4 == 0:
        ko_to_en[tags[i].text] = tags[i + 1].text

# API
url = "https://solved.ac/api/v3/problem/lookup"
headers = {"Content-Type": "application/json"}

# Allowed extensions
extensions = ["cpp", "py"]

# Get problem number list from folder 'algorithm-solution'
file_list = os.listdir("./algorithm-solution")
problems = []
for file in file_list:
    if file.split(".")[1] in extensions:
        problems.append(file.split(".")[0])

# Get all content of README_BASE.md
f = open("./README_BASE.md")
content = f.readlines()
f.close()

# Build dictionary to show solved problems.
algorithm_tags = dict()
for p in problems:
    querystring = {"problemIds": p}
    response = requests.request("GET", url, headers=headers, params=querystring)
    info = json.loads(response.text)
    tags = list(map(lambda x: ko_to_en[x["displayNames"][0]["name"]], info[0]["tags"]))
    for t in tags:
        if t not in algorithm_tags:
            algorithm_tags[t] = []
        algorithm_tags[t].append(p + "번: " + info[0]["titleKo"])

# Write new README.md
f = open("./README.md", "w", encoding="UTF-8")
for line in content:
    f.write(line)
f.write("\n## Solved Problems\n")
for key, value in sorted(algorithm_tags.items()):
    f.write("### " + key + "\n")
    for v in sorted(value):
        f.write('* <a href="https://www.acmicpc.net/problem/{0}"> {1}</a>\n'.format(v.split(":")[0][:-1], v))
    f.write("\n")
f.close()
