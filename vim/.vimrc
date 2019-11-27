:set nu
:set ai
:set tabstop=4
:set shiftwidth=4
:set mouse=a
:set incsearch
:set clipboard=unnamed
 
filetype indent on
 
:inoremap ( ()<Esc>i
:inoremap [ []<Esc>i
:inoremap {<CR> {<CR>}<Esc>ko
:inoremap {{ {}<Esc>i
:inoremap ' ''<Esc>i
:inoremap " ""<Esc>i
 
 
hi LineNr cterm=bold ctermfg=DarkGrey ctermbg=NONE
hi CursorLineNr cterm=bold ctermfg=Green ctermbg=NONE
 
call plug#begin('~/.vim/plugged')
	Plug 'scrooloose/nerdtree'
call plug#end()
 
