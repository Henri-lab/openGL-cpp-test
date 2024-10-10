branch='draw'

until git push -u origin "$branch"; do
    echo "push failded ,retry..."
    sleep 1
done
echo "push successfully"
