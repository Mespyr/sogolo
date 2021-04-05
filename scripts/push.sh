git add .
if [ "$1" == "" ]; then
    echo   "-------------------------------"
    printf "Commit Message: "
    read msg
    echo   "-------------------------------"
else
    msg="$1"
fi
git commit -m "$msg"
git push