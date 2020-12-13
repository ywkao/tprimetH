#!/bin/bash
set -e
pdflatex report; rm *.aux *.log; mv report.pdf latest_report.pdf

dir="/eos/user/y/ykao/www/tables"
cp latest_report.pdf ${dir}; echo ${dir}; ls -lhrt ${dir};
