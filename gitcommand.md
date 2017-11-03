---
title: 2017-10-20未命名文件 
tags: 新建,模板,小书匠
grammar_cjkRuby: true
---


欢迎使用 **{小书匠}(xiaoshujiang)编辑器**，您可以通过==设置==里的修改模板来改变新建文章的内容。  
# Git Global
    $ git config --global user.name "Your Name"  
    $ git config --global user.email "email@example.com"  
    $ git config --global color.ui true  

# Initial a git reposite

    $ git init

# Add and Commit
	$ git add readme.txt  
	$ git commit -m "wrote a readme file"  
	$ git status  
	$ git diff readme.txt  
	$ git diff HEAD -- readme.txt   (工作区和版本库中最新版本比较）  

# Log Reset 
	$ git log   (commit history)  
	$ git log --pretty=oneline  
	$ git log --graph --pretty=oneline --abbrev-commit  
	$ git reset --hard HEAD^  
	$ git reset --hard HEAD^^  
	$ git reset --hard HEAD~15  
	$ git reset --hard 3628164  (commit id)  
	$ git reflog  (command history)  

# Undo changes
	$ git checkout -- readme.txt  （abandon changes in 工作区）让这个文件回到最近一次git commit或git add时的状态。  
	$ git reset HEAD readme.txt    （Unstaged changes of readme.txt) 把暂存区的修改撤销掉（unstage），重新放回工作区：  

	$ rm test.txt  
	$ git rm test.txt  
	$ git checkout --  test.txt   无论工作区是修改还是删除，都可以“一键还原”。  

# Branch
	$ git branch  
	$ git checkout -b dev  
	$ git branch dev  
	$ git checkout dev  
	$ git branch -d dev  
	$ git branch -D feature-vulcan  
	$ git merge --no-ff -m "merge with no-ff" dev

# merge
	$ git merge dev

# Stash
	$ git stash  
	$ git stash list  
	$ git stash apply   stash@{1}  
	$ git stash drop   stash@{1}  
	$ git stash pop  


# remote reposity
	$ git remote add origin git@github.com:michaelliao/learngit.git  
	$ git push -u origin master   (-u for first time push and remote reposite is empty)  
	$ git branch --set-upstream-to origin/branch-name  
	$ git push origin master  
	$ git push origin dev  
	$ git pull  
	$ git remote  
	$ git remote -v  

	$ git clone git@github.com:michaelliao/gitskills.git  
	$ git checkout -b dev origin/dev  

# Tag
	$ git tag v1.0  
	$ git tag  
	$ git tag v0.9 6224937  
	$ git tag -a v0.1 -m "version 0.1 released" 3628164  
	$ git show v0.9  
	$ git push origin v1.0  
	$ git push origin --tags  
	$ git tag -d v0.1  
	$ git push origin :refs/tags/v0.9  

# ignore
	.gitignore

