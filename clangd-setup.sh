#!/bin/sh
# Use in git directory
sed -i -e "s|REPLACEMENT|$(pwd)|" .clangd
