import java.io.File
import java.util.concurrent.TimeUnit

data class GitVersion(val url: String, val uncommittedChanges: String?)

fun readGitVersion(args: GeneratorArgs): GitVersion {
    val dir = args.config.parentFile
    val uncommittedChanges = "git status -s".runCommand(dir)
        ?.takeIf { it.isNotBlank() }
        ?.let { "git working directory not clean: $it" }
    val version = "git rev-parse HEAD".runCommand(dir)!!.trim()
    return GitVersion(args.gitTemplate.format(version), uncommittedChanges)
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
