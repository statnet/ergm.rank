#' @export
InitWtErgmTerm.updown <- function(nw, arglist, ...) {
  # Validate and extract arguments if any (add below if needed)
  a <- check.ErgmTerm(nw, arglist, directed = TRUE, bipartite = FALSE,
                      varnames = NULL, vartypes = NULL, required = NULL,
                      defaultvalues = NULL)

  # Return the list that ergm uses to initialize the term
  list(
    name = "updown",                      # Must match the C changestat prefix
    coef.names = "updown",               # What shows up in summary/model output
    inputs = NULL,                       # No additional inputs (unless you add them)
    dependence = TRUE,                   # This term depends on the network structure
    minval = 0,                           # You can adjust minval/maxval if needed
    maxval = Inf,
    auxiliaries = ~dsociomatrix         
  )
}