PROJECT_CEEDLING_ROOT = "ceedling/vendor/ceedling"
load "#{PROJECT_CEEDLING_ROOT}/lib/ceedling.rb"

Ceedling.load_project ({:config => 'build/project.yml'})

task :default => [ 'test:all' ]
