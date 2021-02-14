#!/usr/bin/env python2
import glob
import subprocess

def prepare_index_php(target):
    index_php = "/eos/user/y/ykao/www/index.php"
    subprocess.call("mkdir -p %s; cp -p %s %s;" % (target, index_php, target), shell=True)

def copy_files(keyword, target):
    prepare_index_php(target)
    png_files = glob.glob(keyword)
    for png in png_files:
        subprocess.call("cp %s %s" % (png, target), shell=True)

def move_files(keyword, target):
    prepare_index_php(target)
    png_files = glob.glob(keyword)
    for png in png_files:
        subprocess.call("mv %s %s" % (png, target), shell=True)


