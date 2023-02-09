CSC := mcs

DLL := BeerProcessor.dll

$(DLL): zleceniePiwo.cs
	$(CSC) -target:library $^ -r:../Common/Common.dll -out:$@

run: $(DLL)
	@mono $(DLL)

clean:
	$(RM) $(DLL)
