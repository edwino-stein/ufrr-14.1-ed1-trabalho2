 #!/bin/sh

#  createFolder.sh
#  
#  Programa auxiliar para criar pastas em ambientes unix.
#
#  Versao 1.0
#
#  Created by Edwino Stein on 29/11/14.
#

folderName=$1 

if [ ! -d "$folderName" ]; then
	mkdir "$folderName";
else
	rm -R "$folderName";
	mkdir "$folderName";
fi