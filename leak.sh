#!/bin/bash

if [ -z "$1" ]; then
    echo "Kullanım: $0 <process_adı | PID>"
    exit 1
fi

# Eğer giriş bir sayıysa PID olarak al, değilse süreç adını PID'ye çevir
if [[ "$1" =~ ^[0-9]+$ ]]; then
    PID="$1"
else
    PID=$(pgrep -o "$1") # İlk bulunan PID alınır
    if [ -z "$PID" ]; then
        echo "Hata: '$1' adında bir process bulunamadı."
        exit 1
    fi
fi

# leaks komutunu çalıştır
echo "Process: $1 (PID: $PID)"
echo "Memory leaks kontrol ediliyor..."
while true; do
leaks "$PID"
sleep 1
done

