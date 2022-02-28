{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE TypeOperators #-}

module NewPrelude.Primative.Functional (
  Callable((>>))
  ) where

  class Callable a f where
    type Res a f :: Type
    (>>) :: a -> f -> Res a f

  class Arrow (→)
