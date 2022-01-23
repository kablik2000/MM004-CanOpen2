#############################################################################
# Creates software identification
#############################################################################


ifeq (,$(USERNAME))
  USERNAME="$(shell $(GIT) config user.name)"
  ifeq (,$(USERNAME))
    $(error undefined USERNAME)
  endif
endif
  # PY - Regular expression operations - https://docs.python.org/3/library/re.html
#  USERNAME_CLEAN:="$(shell $(PYTHON) -c "import re; print(re.compile(r'\s*<.*').sub('','$(USERNAME)'), end='')")"
  USERNAME_CLEAN:="$(shell $(PYTHON) -c "import re; print(re.compile(r'[\w\.-]+@[\w\.-]+').sub('', '$(USERNAME)'))")"
