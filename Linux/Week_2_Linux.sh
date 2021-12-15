#!/bin/bash
#Om dit scipt te runnen moet file.txt, dit script en cd in Home/Documents staan
#cd Documents

mkdir $HOME/photo #maak home/photo aan

echo -n "Geef de maand op wanneer de foto is gemaakt. " 
read monthnum 

for x in file.txt
do
	
	if ((monthnum > 12))
	then 
		echo "Error, give a valid month!"
		exit
	elif ((monthnum < 1))
	then 
		echo "Error, give a valid month!"
		exit
	else
		direct=$monthnum #maandnummer wordt de folder naam in de directory copy, die staan in 'home' 
		echo $direct
	fi


	if [[ -d "$HOME"/photo/"$direct" ]] #bestaat de dir waar de foto is moet al, geeft True of False
	then #True
		cp -v file.txt "$HOME"/photo/"$direct"/"$file" #zoja, kopieer foto en zet erin
		echo "File is copied and in correct directory"
	else #False
		mkdir "$HOME"/photo/"$direct" #juiste dir bestaan niet, maak deze aan in 'photo'
		cp -v file.txt "$HOME"/photo/"$direct"/"$file" #kopieer foto en zet in dir
		echo "Correct directory has been made and file has been copied"
	fi

	og=$(sudo md5sum "$HOME"/Documents/file.txt | cut -d " " -f1) #checksum van de orginele file.txt in HOME/Documents
	copy=$(sudo md5sum "$HOME"/photo/"$direct"/file.txt | cut -d " " -f1) #checksum van de kopie van file.txt in de HOME/photo

	if [ "$og" = "$copy" ] #de 2 checksums vergelijken
	then #True
		rm "$HOME"/Documents/file.txt #Verwijder file.txt in HOME/Documents als de 2 checksums gelijk zijn
		echo "Copy is succesfull, removed de original file"
	else #False
		echo "Copy not succesfull" 	
	fi
done
