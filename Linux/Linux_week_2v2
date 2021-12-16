#!/bin/bash

#cd Documents #.jpg's en dit script moeten in deze directory staan

#mkdir $HOME/photo #maak home/photo aan

echo -n "Kies uit: 'Month' of 'Week':  " 
read m_or_w 
echo "$morw"

for f in *.jpg
do
	if [ "$m_or_w" == "Month" ] 
		then
			monthnum=$(date -r "$f" +%m)
			echo "$monthnum"
		if ((monthnum > 12))
		then 
			echo "Error, no valid month"
			exit
		elif ((monthnum < 1))
		then 
			echo "Error, no valid month!"
			exit
		fi
		
		if [[ -d "$HOME"/photo/Month/"$monthnum" ]] 
		then #True
			cp -v "$f" "$HOME"/photo/Month/"$monthnum"/"$f" 
			echo "File is copied and in correct directory"
		else #False
			mkdir "$HOME"/photo/Month/"$monthnum" 
			cp -v "$f" "$HOME"/photo/Month/"$monthnum"/"$f" 
			echo "Correct directory has been made and file has been copied"
		fi
			
		og_month=$(sudo md5sum "$HOME"/Documents/"$f" | cut -d " " -f1)
		copy_month=$(sudo md5sum "$HOME"/photo/Month/"$monthnum"/"$f" | cut -d " " -f1)
		if [ "$og_month" = "$copy_month" ]
		then
			#rm "$HOME"/Documents/"$f"
			echo "Copy is succesfull, removed de original file"
		else
			echo "Copy not succesfull"
		fi
			
#-------------------------------------------------------------------------			
			
	elif [ "$m_or_w" == "Week" ]
		then
			weeknum=$(date -r "$f" +%W)
			echo "$weeknum"
		if ((weeknum > 52))
		then 
			echo "Error, no valid week"
			exit
		elif ((weeknum < 0))
		then 
			echo "Error, no valid week!"
			exit
							
		fi
		
		
		if [[ -d "$HOME"/photo/Week/"$weeknum" ]] 
		then #True
			cp -v "$f" "$HOME"/photo/Week/"$weeknum"/"$f" 
			echo "File is copied and in correct directory"
		else #False
			mkdir "$HOME"/photo/Week/"$weeknum" 
			cp -v "$f" "$HOME"/photo/Week/"$weeknum"/"$f" 
			echo "Correct directory has been made and file has been copied"
		fi
				
		og_week=$(sudo md5sum "$HOME"/Documents/"$f" | cut -d " " -f1)
		copy_week=$(sudo md5sum "$HOME"/photo/Week/"$weeknum"/"$f" | cut -d " " -f1)

		if [ "$og_week" = "$copy_week" ]
		then
			#rm "$HOME"/Documents/"$f"
			echo "Copy is succesfull, removed de original file"
		else
			echo "Copy not succesfull"
		fi
	fi			
done
