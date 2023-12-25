OUTDIR   := out
BINNAME  := program
PROGRAM  := ${OUTDIR}/${BINNAME}
DATA     := ${OUTDIR}/data
PAPRNAME := paper
PAPER    := ${OUTDIR}/pdf.d/${PAPRNAME}.pdf
TESTDATA := ${DATA}/testing.dat

.PHONY: dieharder ent  view clean

${PAPER}: ${OUTDIR} ${PAPRNAME}.latex references.bib ${DATA}
	latexmk -outdir=$(dir ${PAPER}) -pdfxe -interaction=nonstopmode ${PAPRNAME}.latex

${PROGRAM}: ${OUTDIR} ${BINNAME}.cpp
	g++ -O2 -std=c++11 ${BINNAME}.cpp -o ${PROGRAM}


${DATA}: ${OUTDIR} ${PROGRAM}
	mkdir -p ${DATA} && cd ${OUTDIR} && ./${BINNAME}
	convert ${DATA}/test.bmp ${DATA}/test.eps

${TESTDATA}: ${OUTDIR} ${PROGRAM}
	mkdir -p ${DATA} && cd ${OUTDIR} && ./${BINNAME} --testing


ent: ${TESTDATA}
	ent ${TESTDATA}

dieharder: ${TESTDATA}
	dieharder -a -g 202 -f ${TESTDATA}


${OUTDIR}:
	mkdir -p ${OUTDIR}

view: ${PAPER}
	zathura ${PAPER}


clean:
	rm -rf ${OUTDIR}
