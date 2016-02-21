 #!/bin/sh

#  run.sh
#  
#  Shellscript para compilar e executar o trabalho 2 de estrutura de dados.
#
#  Versao 1.0
#
#  Created by Edwino Stein on 29/11/14.
#

# ************** Incoações **************

compiler="./compile.sh";

invocation="trabalho2.cpp"

# ************** Sub-rotinas **************

chmod +x $compiler;
chmod +x "./createFolder.sh"
invocation="$compiler $invocation";

echo "********************************************************";
echo "*                                                      *";
echo "*          COMPILANDO E INICIANDO O PROGRAMA           *";
echo "*                                                      *";
echo "********************************************************";
echo "";



if [  -d "build/" ]; then
	rm -R "build/";
fi

bash -c "$invocation";

exit 0