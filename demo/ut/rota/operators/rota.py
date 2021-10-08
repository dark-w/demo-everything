#!/usr/bin/env python3

import sys
import os
import re
from subprocess import run, PIPE, SubprocessError
from parse import parse
from importlib import import_module

if len(sys.argv) != 2:
    print('usage {} <source file>'.format(sys.argv[0]))
    exit(1)

# FIXME
fn = os.path.realpath(sys.argv[1])
mod_name = os.path.basename(os.path.dirname(fn))

# FIXME
cpath = os.path.realpath(__file__)
cwd = os.path.dirname(cpath)
if cwd != os.getcwd():
    os.chdir(cwd)

issue_mod = import_module('mod.' + mod_name)
if issue_mod is None:
    print('No such module: ' + mod_name)
    exit(1)

cases = issue_mod.cases
if cases is None or len(cases) == 0:
    print("invalid modlule!")
    exit(1)

# FIXME
os.chdir(os.path.dirname(fn))
_, ext = os.path.splitext(fn)
if ext == '.java':
    cmd = 'java ' + fn
elif ext == '.cc':
    out, _ = os.path.splitext(os.path.basename(fn))
    cmd = 'g++ -o {} {} && ./{}'.format(out, os.path.basename(fn), out)
elif ext == '.py':
    cmd = 'python3 ' + fn
else:
    print('Source type "{}" not suppported yet!'.format(ext))
    exit(1)

print(cmd)

try:
    res = run(cmd, shell=True, stdout=PIPE, text=True)
    if res.returncode != 0:
        exit(1)
except SubprocessError as err:
    print(err)
    exit(1)

lines = res.stdout.split('\n')
if len(lines) == 0:
    print("invalid output!")
    exit(1)

case_index = 0
line_index = 0
count = 0

line = lines[line_index].strip()
(fmt, check) = cases[case_index]

header = 'No. | Output | Format | Result'
header += '\n' + re.sub(r'[^|]', '-', header)
print(header)

while True:
    res = parse(fmt, line)
    if res is not None and check(*res.fixed):
        count += 1
        line_index += 1
        if line_index == len(lines):
            break
        line = lines[line_index].strip()
    elif count > 0:
        count = 0
        case_index += 1
        if case_index == len(cases):
            break
        (fmt, check) = cases[case_index]
    else:
        count = -1

    if count != 0:
        ln = line_index if count > 0 else line_index + 1  # current line number
        print('{} | `{}` | `{}` | {}'.format(ln, lines[ln - 1], fmt, count > 0))
        if count < 0:
            break
