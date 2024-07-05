#!/bin/sh
# load_env.sh

# chmod +x load_env.sh

# Load the .env file and export environment variables
if [ -f .env ]; then
  export $(cat .env | grep -v '^#' | xargs)
  echo "Environment variables loaded:"
  env | grep DB_
fi