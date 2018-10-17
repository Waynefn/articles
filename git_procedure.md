# Git procedure and stream intro

## fork from shared repo (remote)

```
fork
```

## clone/update from remote to local

(e.g.: $address = https://www.github.com/xxx/yyy)

+ clone:

```
git clone $address
```

+ update:

```
git fetch $address
```

## * create a new branch (or do it later)

(e.g.: $newbranch = NO-ISSUE_do_something)

```
git branch $newbranch
```

## change work branch

```
git checkout $branch
```

## do some changes in `$file` of `$newbranch`

## look changes

```
git diff
```

> If you did not create new branch at step ( * ),
> You can create a new branch by input
> `git checkout -b $newbranch`
> 


## save change to local index
only one file:

```
git add $file
```

all files:

```
git add .
```

## commit

```
git commit -m "$description"  $file
```
You should write description like `NO-ISSUE Revise code style`

## push to remote

```
git push origin $newbranch
```

If error, try `git push -u` to set an upstream.


## merge new branch with origin

Use git online to pull request.

## fetch new update form server every day

```
git fetch upstream
git merge upstream/master
git push
```

If you want to change commit message, use 

`git commit --amend`
and 
`git push --force  origin $branchname`



## To create a pull request

1. make some changes
2. checkout -b new_branch_name
3. checkout add .
4. commit and add some description (One line)
5. push origin new_branch_name
6. go to git, compare master with new branch
7. pull request

