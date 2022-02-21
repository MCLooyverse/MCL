module Wrapper(
  Wrapper(..),
  DefWrapper(..)
  ) where
  import Prelude()

  class DefWrapper w a | w -> a where
    dwrap :: a -> w
    undwrap :: w -> a

  class Wrapper w a where
    wrap :: a -> w
    unwrap :: w -> a


  instance (Wrapper w x, Wrapper x y) => Wrapper w y where
    wrap = wrap ∘ wrap
