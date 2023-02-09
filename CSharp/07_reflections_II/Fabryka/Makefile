CSC := mcs

EXE := Fabryka.exe

$(EXE): Fabryka.cs
	$(CSC) $^ -out:$@

run: $(EXE)
	@mono $(EXE)

clean:
	$(RM) $(EXE)
