 @Override
    public void exitMethod_call(marParser.Method_callContext ctx) {
        int typeTokenType = ctx.start.getType();
        Symbol.Type type = marCompiler.getType(typeTokenType);
        String functionName = ctx.ID().toString();
        Symbol s = current.resolve(ctx.ID().toString());
        System.out.println(s);
        if(!global.contains(functionName)){
            errors  += "Function "+ "\"" + functionName + "\"" + " don't exist";
        }
        else {
            //Symbol.Type type = s.getType();
            exprType.put(ctx, s.getType());
            int expressaoSize = ctx.expression().size();
            if (((FunctionSymbol) s).get_arguments().size() > 0) {
                if (((FunctionSymbol) s).get_arguments().size() != expressaoSize) {
                    errors += ("in line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " The expected number of arguments aren't the same, " +
                            "number of arguments expected : " + ((FunctionSymbol) s).get_arguments().size());
                } else if (!verifyArgumentsType((FunctionSymbol) s, ctx)) {
                    errors += ("in line " + ctx.start.getLine() + ":" + ctx.start.getCharPositionInLine() + " Type of the arguments don't match");
                }
                else {
                    exprType.put(ctx,s.getType());
                }
            }
        }
       jumpAddr += 5;
    }