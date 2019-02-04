#! /bin/sh

echo "\033[34mPreparing Server...\033[0m"
cp ~/.brew/Cellar/cmu-pocketsphinx/*/bin/pocketsphinx_continuous server/pocketsphinx_continuous
cd server
npm install
echo "\033[34mPreparing Client...\033[0m"
cd ../client
npm install
cd vueclient
npm install
echo "\033[34mServer and Client Ready\!\033[0m"
