 #!/bin/sh

#  compile.sh
#  
#  Shellscript para compilar pragramas didaticos em C++.
#
#  Versao 1.0
#
#  Created by Edwino Stein on 14/11/14.
#

# Modo de uso: $ ./compile.sh <prog_Principal> [<dependencia_1> <dependencia_2> <dependencia_n>]

# ************** Variaveis globais **************
fileLog="./compile.log";
dirBuild="./build/";

CommonLibSource="common/main.cpp";
fileCommonOutput="common.o";

dependencies='';
success=1;
ARGS=0;
error='';
errorDesc='';
gccCode=0;
warnings=0;

# ************** Sub-rotinas **************

# Função que trata os argumentos
function getArgv (){
	for i in `seq 1 $#`
	do
		eval "ARGS[$i]=\$$i";
	done;
}

# Função que remove apenas a extensão de um arquivo
function removeExtension(){
	fileName=`echo ${1} | cut -f1 -d'.'`
}

# Função que retorna apenas o nome do arquivo sem extensão
function getFileName(){
	fileName=`basename $1`;
	removeExtension $fileName;
}

# Função que realiza a compilação do codigo fonte em um codigo objeto
function compile(){

	success=1;
	errorDesc='';

	removeExtension $1;
	src="./${fileName}.cpp";

	# Verifica se o arquivo fonte existe
	if [ ! -f "$src" ] ; then
	    success=0;
	    gccCode=1;
	    error="O arquivo \"$src\" não é invalido ou não existe!"
	    return;
	fi

	getFileName $1;
	target=$fileName;

	# Remove arquivo objeto antigo, se existir
	if [ -e '${dirBuild}${target}.o' ] ; then
	    rm '${dirBuild}${target}.o'
	fi

	# Compila o arquivo fonte e pega a saida e o codigo do G++
	compilerInvocation="g++ -std=c++11 -Wall -o ${dirBuild}${target}.o -c ${src}";
	bash -c "$compilerInvocation > compile.log 2>&1";
	gccCode=$?;
	
	# Salva o arquivo de log gerado em uma varaivel e o remove
	errorDesc=$(<compile.log);
	rm "compile.log";

	#Verifica se ocorreu algum erro

	if [ $gccCode -ne 0 ];  then
		success=0;
		error="Ocorreu algum erro durante a compilação de \"$src\"";
		return;
	fi

	# Verifica se ocorreu algum alerta
	if [ -n "$errorDesc" ]; then
		success=0;
		error="Ocorreu algum alerta durante a compilação de \"$src\"";
		gccCode=2;
		return;
	fi
}

#Função verifica o nivel do erro e o exibe na tela
function checkError(){

	if [ $success -ne 1 ];  then
		if [ $gccCode -ne 1 ];  then
			echo " Alerta!";
			echo "$error";
			echo;
			echo "********************** DESCRIÇÃO DO ALERTA **********************";
			echo "$errorDesc";
			echo "*****************************************************************";
			echo;
			warnings=$(($warnings + 1));
		else
			echo " Falhou!";
			echo "$error";
			echo;
			echo "********************** DESCRIÇÃO DO ERRO **********************";
			echo "$errorDesc";
			echo "***************************************************************";
			echo;
			echo "O processo foi abortado!";
			exit 1;
		fi
	else
		echo " OK!";
	fi

}

# ************** Programa principal **************

#Trata os argumentos
getArgv $@;

#Cria o diretorio onde ficaram os binarios, caso nao exista
if [ ! -d "$dirBuild" ]; then
  echo -n "Criando diretorio \"$dirBuild\"...";
  mkdir "$dirBuild";
  echo " OK"
fi

#Verifica se já a biblioteca common se nao esta compilada, e então a compila
if [ ! -f "${dirBuild}${fileCommonOutput}" ] ; then
	echo -n "Compilando as dependencias comuns...";

	compile "${dirCommonLib}${CommonLibSource}";
	checkError;

	if [ -f "${dirBuild}${fileName}.o" ] ; then
		bash -c "mv ${dirBuild}${fileName}.o ${dirBuild}${fileCommonOutput}"
	fi
fi
dependencies="$dependencies ${dirBuild}${fileCommonOutput}";

# Percorre os argumentos e compila os arquivos fontes
if [ $# -gt 1 ]; then
	for i in `seq 2 $#`
	do
		echo -n "Compilando \"${ARGS[$i]}\"...";
		compile ${ARGS[$i]};
		checkError;

		getFileName ${ARGS[$i]};
		dependencies="$dependencies ${dirBuild}${fileName}.o";
	done;
fi

# Compila o arquivo fonte do programa principal
echo -n "Compilando o programa principal \"${ARGS[1]}\"...";
compile ${ARGS[1]};
checkError;
main=$fileName;

dependencies="$dependencies ${dirBuild}${main}.o";

#Finalmente gera o arquivo executavel
echo "Montando executavel \"${dirBuild}${main}\"...";

linkerInvocation="g++ -std=c++11 -Wall -Werror -o ${dirBuild}${main} ${dependencies}";
bash -c "$linkerInvocation";
if [ $? -ne 0 ];  then
	echo;
	echo "**** Houve erros durante a linkedição! ****";
	exit 1;
fi

#Analiza se ocorreu algo errado
if [ $warnings -ne 0 ];  then
	echo "Ocorreram $warnings alertas durante a compilação! Precione qualquer tecla para continuar...";
	read KEY;
else
	echo "Não houve erros durante a compilação! Executando \"$main\"...";
	sleep 1s;
fi

# Executa o programa
bash -c "./build/$main";