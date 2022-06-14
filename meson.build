project('gamesInC', 'c', default_options: ['warning_level=3', 'debug=true', 'optimization=g'])
thread_dep = dependency('threads')
src_files = ['main.c', 'jeffrey.c', 'utils.c']
executable('game', src_files, dependencies : thread_dep)