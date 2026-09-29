// Apply a TSV of symbols to the current program (headless-friendly).
//
// TSV columns:  addr(hex)  size  kind(F|D)  name
//   F = function entry (disassemble + create/rename function)
//   D = data/label
//
// Usage (headless):
//   -postScript ApplyPsxSym.java <path-to.tsv>
//
// @category PSX
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.io.BufferedReader;
import java.io.FileReader;

public class ApplyPsxSym extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 1) {
            println("ApplyPsxSym: need a TSV path argument");
            return;
        }
        int nFunc = 0, nData = 0, nFail = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(args[0]))) {
            String line;
            while ((line = br.readLine()) != null) {
                if (line.isBlank()) continue;
                String[] c = line.split("\t");
                if (c.length < 4) continue;
                long a = Long.decode(c[0]);
                String kind = c[2];
                String name = c[3];
                Address addr = toAddr(a);
                try {
                    if (kind.equals("F")) {
                        disassemble(addr);
                        Function f = getFunctionAt(addr);
                        if (f == null) f = createFunction(addr, name);
                        if (f != null) {
                            f.setName(name, SourceType.USER_DEFINED);
                            nFunc++;
                        } else {
                            createLabel(addr, name, true, SourceType.USER_DEFINED);
                            nFail++;
                        }
                    } else {
                        createLabel(addr, name, true, SourceType.USER_DEFINED);
                        nData++;
                    }
                } catch (Exception e) {
                    nFail++;
                }
            }
        }
        println(String.format("ApplyPsxSym: %d functions, %d data labels, %d failures",
                nFunc, nData, nFail));
    }
}
