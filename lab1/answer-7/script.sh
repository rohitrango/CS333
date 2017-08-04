i=0
while (( i++ < 30000 )); do
  cp ./files/foo.pdf "./files/foo$i.pdf"
done