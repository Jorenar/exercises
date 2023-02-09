CSC := mcs

DLL := Common.dll

$(DLL): IZlecenie.cs
	$(CSC) -target:library $^ -out:$@

run: $(DLL)
	@mono $(DLL)

clean:
	$(RM) $(DLL)
