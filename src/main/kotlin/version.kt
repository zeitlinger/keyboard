import java.io.File
import java.util.concurrent.TimeUnit

fun readGitVersion(gitFile: GitFile, name: String): String {
    val dir = if (gitFile.file.isFile) gitFile.file.parentFile else gitFile.file
    val uncommittedChanges = "git status -s".runCommand()
        ?.takeIf { it.isNotBlank() }
        ?.let { "git working directory not clean: $it" }
        ?.also {
            println(it)
        }
    val version = if (uncommittedChanges != null ) "uncommitted changes" else  "git rev-parse HEAD".runCommand()!!.trim()
    return gitFile.gitTemplate.format(version, name)
}

fun String.runCommand(): String {
    val parts = this.split("\\s".toRegex())
    val proc = ProcessBuilder(*parts.toTypedArray())
        .directory(File("."))
        .redirectOutput(ProcessBuilder.Redirect.PIPE)
        .redirectError(ProcessBuilder.Redirect.PIPE)
        .start()

    proc.waitFor(2, TimeUnit.SECONDS)
    return proc.inputStream.bufferedReader().readText()
}
