import java.io.File
import java.util.concurrent.TimeUnit

fun readGitVersion(args: GeneratorArgs): String {
    val dir = args.config.parentFile
    "git status -s".runCommand(dir)?.let {
        if (it.isNotBlank()) {
            throw IllegalStateException("git working directory not clean: $it")
        }
    }
    val version = "git rev-parse HEAD".runCommand(dir)!!.trim()
    return args.gitTemplate.format(version)
}

fun String.runCommand(workingDir: File): String? {
    val parts = this.split("\\s".toRegex())
    val proc = ProcessBuilder(*parts.toTypedArray())
        .directory(workingDir)
        .redirectOutput(ProcessBuilder.Redirect.PIPE)
        .redirectError(ProcessBuilder.Redirect.PIPE)
        .start()

    proc.waitFor(2, TimeUnit.SECONDS)
    return proc.inputStream.bufferedReader().readText()
}
