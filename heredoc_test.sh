export LOL=lustig
cat -n <<EOF
echo hier $LOL
EOF
echo ja hier ist ein befehl diggi

cat -n << "EOF"
echo $LOL ist nicht lustig
EOF
echo ja hier ist einn och befehl diggi

echo jetzt warten wir mal 3 sekunden
sleep 3
echo und jetzt ein here doc das nicht sauber endet
cat -n << "EOF"
echo $LOL
