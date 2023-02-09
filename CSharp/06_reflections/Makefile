CSC := mcs

EXE := Reflections.exe

$(EXE): Reflections.cs Customer.cs
	$(CSC) $^ -out:$@

run: $(EXE)
	@mono $(EXE)

clean:
	$(RM) $(EXE)
