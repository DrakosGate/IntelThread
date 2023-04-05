/**
* RocketThread RocketPlugins Space Automation
*/

job("Feature CI") {

    git { clone = false }

    startOn {
        gitPush {
            branchFilter {
                +"refs/heads/feature/*"
            }
        }
    }

    container(displayName = "Branch-Build", image = "rocketwerkz.registry.jetbrains.space/p/plugins/containers/build:0.1.4") {

        shellScript {

            content = """
                git clone ssh://git@git.jetbrains.space/rocketwerkz/plugins/Workbench.git
                cd Workbench
                git clone -b ${'$'}(echo ${'$'}JB_SPACE_GIT_BRANCH | sed -e s?refs/heads/??) --single-branch \
                    ssh://git@git.jetbrains.space/rocketwerkz/plugins/RocketThread.git plugins/RocketThread \
                    --recurse-submodules
                just setup networking
            """
        }
    }
}

job("Main CI") {

    git { clone = false }

    startOn {
        gitPush {
            branchFilter {
                +"refs/heads/main"
            }
        }
    }

    container(displayName = "Main-Build", image = "rocketwerkz.registry.jetbrains.space/p/plugins/containers/build:0.1.4") {

        shellScript {

            content = """
                git clone ssh://git@git.jetbrains.space/rocketwerkz/plugins/Workbench.git
                cd Workbench
                just setup networking
            """
        }
    }
}
