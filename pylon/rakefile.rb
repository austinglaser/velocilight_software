PROJECT_CEEDLING_ROOT = "../modules/ceedling/vendor/ceedling"
load "#{PROJECT_CEEDLING_ROOT}/lib/ceedling.rb"

Ceedling.load_project ({:config => 'build_ceedling/project.yml'})

task :default => [ 'test:all' ]
