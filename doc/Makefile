all:
	@echo -e "\033[33m< Generating Doc >\033[37m"
	@doxygen config		1>/dev/null
	@echo -e "\033[33m< Generating Pdf >\033[37m"
	@make -C latex/		1>/dev/null
	@echo -e "\033[33m< Doc generated >\033[37m"
	@cp latex/refman.pdf ./

clean:
	@echo -e "\033[34m< Cleaning Doc >\033[37m"
	@rm -rfv html/* latex/* man/

distclean: clean
	@if test -e latex ; then rm -fr latex ; fi 1>/dev/null
	@if test -e html ; then rm -fr html ; fi 1>/dev/null
	@if test -e man ; then rm -fr man ; fi 1>/dev/null
	@rm -fr refman.pdf
