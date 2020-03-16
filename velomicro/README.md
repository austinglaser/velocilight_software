#nRF5 SDK Template
==================

# Subtrees

To include content from shared repositories, this project uses git's subtree
functionality. If you're just cloning to build, or only making changes to files
belonging to this repository, you can for the most part ignore this section.

*However*, if any changes touch files under `nrf5-sdk/` or `modules/`, or if you
want to update the content under these directories to the latest, you should set
up the repository properly.

## Extra Remotes

Subtrees require the repository to have multiple remotes. Unfortunately, git
provides no functionality to automatically set these values, so you must run the
following commands:

    $ git remote add nrf5-sdk-remote git@git.boulderes.com:bes-internal/nrf5-sdk.git
    $ git remote add modules-remote git@git.boulderes.com:bes-internal/modules.git

## Pulling subtree changes

To update to the latest on either of the remotes, you can use the following
commands:

    $ git subtree pull --prefix=nrf5-sdk nrf5-sdk-remote master --squash
    $ git subtree pull --prefix=modules modules-remote master --squash

The `--squash` is important to keep the local history from getting cluttered

## Pushing subtree changes

The following commands will push to one of the subtrees:

    $ git subtree push --prefix=nrf5-sdk nrf5-sdk-remote <branch>
    $ git subtree push --prefix=modules modules-remote <branch>

Generally, you do NOT want to push to master. Instead, push to a
feature/bugfix/whatever branch and open a merge request.
