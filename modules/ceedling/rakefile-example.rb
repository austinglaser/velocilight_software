require 'ceedling'

Ceedling.load_project ({:config => 'build_ceedling/project.yml'})

task :default => [ 'test:all' ]
