 function Component() {
 }
 
 Component.prototype.createOperations = function() {
  component.createOperations();
 
 if ( installer.value("os") === "win" ) {
  component.addOperation(
  "CreateShortcut",
  "@TargetDir@/dermatoscopio.exe",
  "@StartMenuDir@/Dermasoft.lnk"
  );
  
  component.addOperation(
  "CreateShortcut",
  "@TargetDir@/Desinstalar.exe",
  "@StartMenuDir@/Desinstalar.lnk"
  );
  }
 }