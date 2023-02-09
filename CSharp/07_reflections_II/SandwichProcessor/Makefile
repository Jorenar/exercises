CSC := mcs

DLL := SandwichProcessor.dll

$(DLL): zlecenieKanapka.cs
	$(CSC) -target:library $^ -r:../Common/Common.dll -out:$@

run: $(DLL)
	@mono $(DLL)

clean:
	$(RM) $(DLL)
