#!/bin/bash

if [ $1 = "help" ]; then
    if [ $# = 1 ]; then
        echo 'пердпологается: ./try21.sh "suffix" "prefix" "directory"'
        echo "suffix - суффикс по которому должен вестись поиск (обязательно) (c точкой)"
        echo "prefix - префикс который побавляется в названию файла (обязательно) "
        echo "directory - директория в которой должно вестись работа"
        exit 4
    else
        echo неверное кол-во аргументов
        exit 1
    fi
else 
    if [ $# != 2 ] && [ $# != 3 ]; then
        echo неверное кол-во аргументов
        exit 1
    fi
fi

if [ -e $3 ]; then
    if [ -d $3 ];then
        directory=$3
    else
        echo нет такой директории
        exit 2
    fi
else
    directory = '.'
fi

if ! [[ $1 =~ ^\..*$ ]]; then
    echo неправильно написанн суффикс
    exit 3
fi

# Префикс, который нужно добавить
prefix=$2
# суффикс по которому ведется поиск
suffix=$1

# Перебираем все файлы с указанным суффиксом в заданном каталоге
for file in "$directory"*"$suffix"; do
    echo $file
    if [ -f "$file" ]; then
        
        dirname=$(dirname "$file")
        basename=$(basename "$file")
        # Получаем базовое имя файла без пути к каталогу и путь к файлу
        # Формируем новое имя файла, добавляя префикс
        newfile="$dirname/$prefix$basename"
        
        mv "$file" "$newfile"
    
        echo "переименован '$file' в '$newfile'"
    fi
done