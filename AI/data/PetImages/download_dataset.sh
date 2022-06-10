#!/usr/bin/env sh

curl -OL https://download.microsoft.com/download/3/E/1/3E1C3F21-ECDB-4869-8368-6DEBA77B919F/kagglecatsanddogs_5340.zip
unzip kagglecatsanddogs_5340.zip
mv PetImages/Cat ./cats
mv PetImages/Dog ./dogs
